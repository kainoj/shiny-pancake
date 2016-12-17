{
  'targets': [
    {
    	"cflags": ["-std=c++11"],
    	'cflags_cc+': ['-frtti'],
    	'cflags_cc!': ['-fno-rtti'],
      'target_name': 'pancake',
      'defines': [ 'V8_DEPRECATION_WARNINGS=1' ],
      'sources': [ 
      	'source/pancake.cc',
      	'source/World.cpp',
      	'source/utilities.cpp',
      	'source/Entities/Bullet.cpp'
       ]
    }
  ]
}
