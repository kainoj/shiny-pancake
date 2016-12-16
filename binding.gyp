{
  'targets': [
    {
    	"cflags": [
			  "-std=c++11"
			],
      'target_name': 'pancake',
      'defines': [ 'V8_DEPRECATION_WARNINGS=1' ],
      'sources': [ 'source/pancake.cc' ]
    }
  ]
}
