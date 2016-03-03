MRuby::Build.new do |conf|
  toolchain :gcc
  enable_test
  conf.gembox 'default'
  conf.gem :github => 'mattn/mruby-iconv' do |g|
    g.linker.libraries.delete 'iconv'
  end
  conf.gem '#{MRUBY_ROOT}/..'
end
