project('huffmanzip', ['cpp', 'c'], 
  version: '0.1.1',
  meson_version: '>= 0.59.0',
  default_options: [ 
    'warning_level=2',
    'cpp_std=gnu++20',
  ],
)

config_data = configuration_data()
config_data.set_quoted('LOCALEDIR', join_paths(get_option('prefix'), get_option('localedir')))
config_data.set_quoted('GETTEXT_PACKAGE', meson.project_name())

configure_file(
  output: 'config.h',
  configuration: config_data
)

config_h_dir = include_directories('.')

i18n = import('i18n')
gnome = import('gnome')

subdir('data')
subdir('src')
subdir('po')

gnome.post_install(
  glib_compile_schemas: true,
)
