SHELL=/bin/bash
CXX=g++
NAME:=libsocket-can-java

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
DIRS=stamps obj $(JAVA_DEST) $(JAVA_TEST_DEST) $(LIB_DEST) $(JAR_DEST)
JNI_DIR=jni
JNI_CLASSES=io.openems.edge.socketcan.driver.CanSocket
JAVAC_FLAGS=-g -Xlint:all
CXXFLAGS=-I./include -Iclasses -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions \
	-fstack-protector --param=ssp-buffer-size=4 -fPIC -Wno-unused-parameter \
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
	@echo "JAVAC JAVA"
	$(JAVAC) $(JAVAC_FLAGS) -d $(JAVA_DEST) $(sort $(JAVA_SRC))
	@touch $@

stamps/compile-test: stamps/compile-src $(JAVA_TEST_SRC)
	$(JAVAC) $(JAVAC_FLAGS) -cp $(JAVA_DEST) -d $(JAVA_TEST_DEST) \
	$(sort $(JAVA_TEST_SRC))
	@touch $@

stamps/generate-jni-h: stamps/compile-src
	@echo "GEN HEADER"
	$(JAVAH) classes src/io/openems/edge/socketcan/driver/CanSocket.java 
	@touch $@

stamps/compile-jni: stamps/generate-jni-h $(JNI_SRC)
	@echo "CC JNI"
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared -o $(LIB_DEST)/lib$(SONAME).so \
		$(sort $(filter %.cpp,$(JNI_SRC)) $(filter %.c,$(JNI_SRC)))
	@touch $@
        
stamps/create-jar: stamps/compile-jni $(JAR_MANIFEST_FILE)
	@echo "JAVAC JAR"
	$(JAR) cMf $(JAR_DEST_FILE) $(JAR_MANIFEST_FILE) lib -C $(JAVA_DEST) .
	@touch $@

.PHONY: check
check: stamps/create-jar stamps/compile-test
		$(JAVA) -ea -cp $(JAR_DEST_FILE):$(JAVA_TEST_DEST) \
                -Xcheck:jni \
                org.clehne.revpi.canbus.CanSocketTest
