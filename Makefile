SHELL=/bin/bash
CXX=./zig/zig c++
NAME:=libsocket-can-java
JAVA_HOME:=/usr/lib/jvm/java-17-openjdk-amd64/

JAVA_INCLUDES=-I$(JAVA_HOME)/include/linux -I$(JAVA_HOME)/include
JAVA=$(JAVA_HOME)/bin/java
JAVAC=$(JAVA_HOME)/bin/javac
JAVAH=$(JAVA_HOME)/bin/javac -h 
JAR=$(JAVA_HOME)/bin/jar
JAVA_SRC:=$(shell find src -type f -and -name '*.java')
JAVA_TEST_SRC:=$(shell find src.test -type f -and -name '*.java')
JNI_SRC:=$(shell find jni -type f -and -regex '^.*\.\(c\|cpp\|h\)')
JAVA_DEST=classes
JAVA_TEST_DEST=classes.test
LIB_DEST=lib
JAR_DEST=dist
JAR_DEST_FILE=$(JAR_DEST)/$(NAME).jar
JAR_MANIFEST_FILE=META-INF/MANIFEST.MF
DIRS=stamps obj $(JAVA_DEST) $(JAVA_TEST_DEST) $(LIB_DEST)/x86_64 $(LIB_DEST)/armv7a $(JAR_DEST)
JNI_DIR=jni
JNI_CLASSES=io.openems.edge.socketcan.driver.CanSocket
JAVAC_FLAGS=-g -Xlint:all
CXXFLAGS=-Iclasses -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions \
	--param=ssp-buffer-size=4 -fPIC -Wno-unused-parameter \
	-pedantic -D_REENTRANT -D_GNU_SOURCE \
	$(JAVA_INCLUDES)

SONAME=jni_socketcan
LDFLAGS=-Wl,-soname,$(SONAME)

.DEFAULT_GOAL := all
.LIBPATTERNS :=
.SUFFIXES:

.PHONY: all
all: stamps/create-jar stamps/compile-test

.PHONY: clean
clean:
	$(RM) -r $(DIRS) $(STAMPS) $(filter %.h,$(JNI_SRC))
	$(RM) -r $(JNI_DIR)/*.h
	$(RM) -r $(JNI_DIR)/*.gch
	find . -name "*.class" -exec rm {} \;  

stamps/dirs:
	mkdir $(DIRS)
	@touch $@

stamps/compile-src: stamps/dirs $(JAVA_SRC)
	$(call msg,JAVAC JAVA,$@)
	$(Q)$(JAVAC) $(JAVAC_FLAGS) -d $(JAVA_DEST) $(sort $(JAVA_SRC))
	@touch $@

stamps/compile-test: stamps/compile-src $(JAVA_TEST_SRC)
	$(Q)$(JAVAC) $(JAVAC_FLAGS) -cp $(JAVA_DEST) -d $(JAVA_TEST_DEST) $(sort $(JAVA_TEST_SRC))
	@touch $@

stamps/generate-jni-h: stamps/compile-src
	$(call msg,GEN HEADER,$@)
	$(Q)$(JAVAH) classes $(sort $(JAVA_SRC))
	@touch $@

stamps/compile-native-x86_64: stamps/generate-jni-h $(JNI_SRC)
	$(call msg,CXX JNI Linux x86/64,$@)
	$(Q)$(CXX) -target x86_64-linux-gnu $(CXXFLAGS) $(LDFLAGS) -shared -o $(LIB_DEST)/x86_64/lib$(SONAME).so \
		$(sort $(filter %.cpp,$(JNI_SRC)) $(filter %.c,$(JNI_SRC)))
	@touch $@

stamps/compile-native-armv7a: stamps/generate-jni-h $(JNI_SRC)
	$(call msg,CXX JNI Linux ARM,$@)
	$(Q)$(CXX) -target arm-linux-gnueabihf $(CXXFLAGS) $(LDFLAGS) -shared -o $(LIB_DEST)/armv7a/lib$(SONAME).so \
		$(sort $(filter %.cpp,$(JNI_SRC)) $(filter %.c,$(JNI_SRC)))
	@touch $@

stamps/create-jar: stamps/compile-native-x86_64 stamps/compile-native-armv7a $(JAR_MANIFEST_FILE)
	$(call msg,$(java -version),$@)
	$(call msg,JAVAC JAR,$@)
	$(Q)$(JAR) cMf $(JAR_DEST_FILE) $(JAR_MANIFEST_FILE) lib -C $(JAVA_DEST) .
	@touch $@

.PHONY: test
test: stamps/create-jar stamps/compile-test
		$(JAVA) -ea -cp $(JAR_DEST_FILE):$(JAVA_TEST_DEST) \
                -Xcheck:jni \
				io.openems.edge.socketcan.driver.CanSocketTest
