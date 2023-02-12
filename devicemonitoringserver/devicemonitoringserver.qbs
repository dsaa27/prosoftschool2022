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
            "../BaseEncoderExecutor.h",
            "../messageencoder.cpp",
            "../messageencoder.h",
            "../messageserializaror.h",
            "C:/Users/User/Desktop/messageserializator.cpp.2E23542E06C8D1A7.idx",
            "C:/Users/User/Desktop/messageserializator.cpp.o",
        ]
    }
}
