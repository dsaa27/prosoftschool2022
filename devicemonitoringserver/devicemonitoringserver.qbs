import qbs

CppApplication {
    files: [

    ]

    consoleApplication: true
    cpp.cxxLanguageVersion: "c++17"
    cpp.includePaths: product.sourceDirectory

    Group {
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }

    Group {
        name: "C++"
        prefix: "**/"
        files: [
            "*.h",
            "*.cpp",
            "../encoder/baseencoderexecutor.h",
            "../encoder/messageencoder.cpp",
            "../encoder/messageencoder.h",
            "../messageserializator.h",
            "../messageserializator.cpp",
            "../encoder/ROT3.cpp",
            "../encoder/ROT3.h",
            "../Mirror.cpp",
            "../Mirror.h",
            "../Multiply41.cpp",
            "../Multiply41.h"
        ]
    }
}
