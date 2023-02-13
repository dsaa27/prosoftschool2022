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
            "../baseencoderexecutor.h",
            "../messageencoder.cpp",
            "../messageencoder.h",
            "../baseencoderexecutor.h",
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
