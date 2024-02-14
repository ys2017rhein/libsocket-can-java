package io.openems.edge.socketcan.driver;

import java.io.BufferedReader;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URI;
import java.net.URISyntaxException;
import java.nio.file.FileSystem;
import java.nio.file.FileSystemNotFoundException;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.ProviderNotFoundException;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.stream.Stream;

public final class StaticLibLoaderUtils {

	/**
     * Temporary directory which will contain the so / dll / dynlib.
     */
    private static File temporaryDir;

	private StaticLibLoaderUtils() { } 

	/**
     * Load a library with OS and architecture detection. The idea is that libraries are found
     *
     * @param folder The folder of the library with forward slashes starting with '/' e.g. '/jni'
     * @param folder the base name of the library which is then translated to system names socketcan is translated
     *               to socketcan.dll on windows or libsocketcan.dynlib on macOS or libsocketcan.so on Linux.
     * @return True if the library is loaded successfully
	 * @throws URISyntaxException 
     */
    public static boolean loadLibraryFromJarWithOSDetection(String folder,String libraryName) {
        String systemLibraryName = System.mapLibraryName(libraryName);
        List<String> foundLibraries;
        try {
            foundLibraries = listResources(folder);
        } catch (URISyntaxException | IOException e) {
            throw new RuntimeException(e);
        }

        if(foundLibraries.size() == 0 ){
            System.err.println("No native JNI libraries found in JAR archive");
        }
        for(String resourceName : foundLibraries){
            if(resourceName.contains(systemLibraryName)){

                // System.err.println("Try to load JNI library " + resourceName + " from JAR archive.");
                try{
                    StaticLibLoaderUtils.loadLibraryFromJar(resourceName);
                    System.err.println("Native library library " + resourceName + " loaded!");
                    return true;
                } catch (IOException | UnsatisfiedLinkError e){
                    // System.err.println("Failed to load library " + resourceName  + " potentially attempting others.\n" + e.getMessage());
                }
            }
        }
        return false;
    }


    /**
     * Lists all resources in a folder. This works for resources in a JAR or on disk
     * @param path the path with the last '/' removed
     * @return An alphabetically ordered list of resources.
     * @throws URISyntaxException When an incorrect URI format is used
     * @throws IOException When reading goes wrong.
     */
    private static List<String> listResources(String path) throws URISyntaxException, IOException {
        return List.of(path + "/armv7a/libjni_socketcan.so", path + "/x86_64/libjni_socketcan.so");
    }

    /**
     * Loads library from current JAR archive
     * 
     * The file from JAR is copied into system temporary directory and then loaded. The temporary file is deleted after
     * exiting.
     * Method uses String as filename because the pathname is "abstract", not system-dependent.
     * 
     * @param path The path of file inside JAR as absolute path (beginning with '/'), e.g. /package/File.ext
     * @throws IOException If temporary file creation or read/write operation fails
     * @throws IllegalArgumentException If source file (param path) does not exist
     * @throws IllegalArgumentException If the path is not absolute or if the filename is shorter than three characters
     * (restriction of {@link File#createTempFile(java.lang.String, java.lang.String)}).
     * @throws FileNotFoundException If the file could not be found inside the JAR.
     */
    public static void loadLibraryFromJar(String path) throws IOException {
 
        if (null == path || !path.startsWith("/")) {
            throw new IllegalArgumentException("The path has to be absolute (start with '/').");
        }
 
        // Obtain filename from path
        String[] parts = path.split("/");
        String filename = (parts.length > 1) ? parts[parts.length - 1] : null;
 
        // Check if the filename is okay
        if (filename == null || filename.length() < 3) {
            throw new IllegalArgumentException("The filename has to be at least 3 characters long.");
        }
 
        // Prepare temporary file
        if (temporaryDir == null) {
            temporaryDir = createTempDirectory("lib");
            temporaryDir.deleteOnExit();
        }

        File temp = new File(temporaryDir, filename);

        try (InputStream is = StaticLibLoaderUtils.class.getResourceAsStream(path)) {
            Files.copy(is, temp.toPath(), StandardCopyOption.REPLACE_EXISTING);
            // System.err.println("Copied library to " + temp.getAbsolutePath() + " delete after use.");
        } catch (IOException e) {
            temp.delete();
            throw e;
        } catch (NullPointerException e) {
            temp.delete();
            throw new FileNotFoundException("File " + path + " was not found inside JAR.");
        }

        try {
            System.load(temp.getAbsolutePath());
        } finally {
            if (isPosixCompliant()) {
                // Assume POSIX compliant file system, can be deleted after loading
                temp.delete();
            } else {
                // Assume non-POSIX, and don't delete until last file descriptor closed
                temp.deleteOnExit();
            }
        }
    }

    private static boolean isPosixCompliant() {
        try {
            return FileSystems.getDefault()
                    .supportedFileAttributeViews()
                    .contains("posix");
        } catch (FileSystemNotFoundException
                | ProviderNotFoundException
                | SecurityException e) {
            return false;
        }
    }

    private static File createTempDirectory(String prefix) throws IOException {
        String tempDir = System.getProperty("java.io.tmpdir");
        File generatedDir = new File(tempDir, prefix + System.nanoTime());
        
        if (!generatedDir.mkdir())
            throw new IOException("Failed to create temp directory " + generatedDir.getName());
        
        return generatedDir;
    }
}
