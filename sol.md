Java.perform(function () {

    var AudioTrack = Java.use("android.media.AudioTrack");

    AudioTrack.write.overload('[B', 'int', 'int').implementation = function(buffer, offset, size) {

        console.log("Audio buffer intercepted: " + size);

        // Convert Java byte[] to JS array
        var data = Java.array('byte', buffer);

        // Example analysis
        console.log("First bytes:", data.slice(0,16));

        // Return original call
        return this.write(buffer, offset, size);
    };
});
