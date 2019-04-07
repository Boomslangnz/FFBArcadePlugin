var ini = require('ini');
var fs = require('fs');
var myArgs = process.argv.slice(2) || [];
var filename = myArgs.length > 0 ? myArgs[0] : (__dirname + '\\FFBPlugin.ini');
var sourceDir = myArgs.length > 1 ? myArgs[1] : __dirname;
var outputDir = myArgs.length > 2 ? myArgs[2] : __dirname;

var o = ini.parse(fs.readFileSync(filename, 'ascii'));
// console.log(JSON.stringify(o) + "\r\n\r\n");

var getSettings = function() {
    var settings = {};
    Object.keys(o.Settings).forEach(function(k) {
        settings[k] = o.Settings[k];
    });
    return settings;
}

if (fs.existsSync(outputDir + "\\dinput8.dll")) {
    console.log("DINPUT8.DLL FOUND");
} else {
    console.log("DINPUT8.DLL NOT FOUND!");
}

Object.keys(o).forEach(function(key) {
    var output = getSettings();
    var folderName = key;
    if (key !== "Settings") {
        var realOutput = Object.assign(output, o[key]);
        // console.log(JSON.stringify(realOutput) + "\r\n\r\n");
        if (!fs.existsSync(outputDir + '\\' + folderName)) {
            fs.mkdirSync(outputDir + "\\" + folderName);
        }
        console.log("Exporting settings for " + folderName);
        fs.writeFileSync(outputDir + "\\" + folderName + "\\FFBPlugin.ini",
        "; " + "*".repeat((" *** FFB Settings for" + folderName + " ***").length) + "\r\n" +
        "; *** FFB Settings for " + folderName + " ***\r\n" + 
        "; " + "*".repeat((" *** FFB Settings for" + folderName + " ***").length) + "\r\n" +
        ini.stringify({ Settings: realOutput }).trim());
        // try {
        //     fs.copyFileSync(sourceDir + "\\SDL2.dll", outputDir + "\\" + folderName + "\\SDL2.dll");
        //     fs.copyFileSync(sourceDir + "\\dinput8.dll", outputDir + "\\" + folderName + "\\dinput8.dll");
        // } catch(e) {
        //     // oh well
        // }
    }
});

// var deleteIfExists = function(fn) {
//     if (fs.existsSync(fn)) {
//         fs.unlinkSync(fn);
//     }
// }

// deleteIfExists(sourceDir + "\\dinput8.exp");
// deleteIfExists(sourceDir + "\\dinput8.lib");
// deleteIfExists(sourceDir + "\\dinput8.dll");
// deleteIfExists(sourceDir + "\\SDL2.dll");
// deleteIfExists(sourceDir + "\\FFBPlugin.ini");

// var deleteFolderRecursive = function(path) {
//     if (fs.existsSync(path)) {
//       fs.readdirSync(path).forEach(function(file, index){
//         var curPath = path + "/" + file;
//         if (fs.lstatSync(curPath).isDirectory()) { // recurse
//           deleteFolderRecursive(curPath);
//         } else { // delete file
//           fs.unlinkSync(curPath);
//         }
//       });
//       fs.rmdirSync(path);
//     }
// }

// if (fs.existsSync(sourceDir + "DInput8Wrapper\\")) {
// console.log("would delete" + sourceDir + "DInput8Wrapper\\");
//  deleteFolderRecursive(sourceDir + "\\DInput8Wrapper\\");   
// }