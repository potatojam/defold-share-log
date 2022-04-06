var LibShareLog = {

    // This can be accessed from the bootstrap code in the .html file
    $ShareLogLibrary: {
        
    },

    ShareLog_Init: function () {
        if (typeof ShareLog !== "undefined") {
            ShareLog.subscribe();
        }
    },
}

autoAddDeps(LibShareLog, '$ShareLogLibrary');
mergeInto(LibraryManager.library, LibShareLog);