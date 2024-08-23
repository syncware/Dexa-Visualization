{
  'targets': [
    {
      'target_name': 'volumeforecast',
      'sources': [ 'volumeforecast.cpp' ],
      'cflags': [ '-fexceptions' ],
      'cflags_cc': [ '-fexceptions' ],
      "include_dirs": [
      "./node_modules/node-addon-api"
      ],
      'defines': [
      'NAPI_CPP_EXCEPTIONS'],
      "conditions": [
          [ "OS=='linux'", {
              "cflags+": [ "-std=c++17", "-fexceptions" ],
              "cflags_c+": [ "-std=c++17", "-fexceptions" ],
              "cflags_cc+": [ "-std=c++17", "-fexceptions" ],
          }],
          [ "OS=='freebsd'", {
              "cflags+": [ "-std=c++17", "-fexceptions" ],
              "cflags_c+": [ "-std=c++17", "-fexceptions" ],
              "cflags_cc+": [ "-std=c++17", "-fexceptions" ],
          }],
          [ "OS=='mac'", {
              "cflags+": [ "-stdlib=libc++" ],
              "xcode_settings": {
                  "OTHER_CPLUSPLUSFLAGS" : [ "-std=c++17", "-stdlib=libc++", "-pthread" ],
                  "OTHER_LDFLAGS": [ "-stdlib=libc++" ],
                  "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                  "MACOSX_DEPLOYMENT_TARGET": "10.7",
                  "CLANG_CXX_LANGUAGE_STANDARD":"c++17",
                  "CLANG_CXX_LIBRARY": "libc++"
              },
          }],
          [
          "OS=='win'", {
            "cflags": [
              "-Wall"
            ],
            "defines": [
              "WIN"
            ],
            "msvs_settings": {
              "VCCLCompilerTool": {
                "ExceptionHandling": "2",
                "DisableSpecificWarnings": [
                  "4244"
                ],
              },
              "VCLinkerTool": {
                "LinkTimeCodeGeneration": 1,
                "OptimizeReferences": 2,
                "EnableCOMDATFolding": 2,
                "LinkIncremental": 1,
              }
            }
          }]
      ]
    }
  ]
}