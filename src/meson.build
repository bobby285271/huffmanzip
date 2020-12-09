huffmanzip_sources = [
  'string-convert.cpp',
  'encode.cpp',
  'decode.cpp',
  'main.cpp',
  'huffmanzip-window.cpp',
]

huffmanzip_deps = [
  dependency('gtkmm-3.0', version: '>= 3.18'),
]

gnome = import('gnome')

huffmanzip_sources += gnome.compile_resources('huffmanzip-resources',
  'huffmanzip.gresource.xml',
  c_name: 'huffmanzip'
)

executable('huffmanzip', huffmanzip_sources,
  dependencies: huffmanzip_deps,
  install: true,
)
