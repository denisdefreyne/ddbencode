### configuration

TARGET_BIN_TEST   = 'ddbencode_test'
TARGET_LIB        = 'ddbencode.dylib'

SRCS_LIB          = FileList[ 'src/ddbencode/*.c', 'vendor/cobject/src/cobject/*.c' ]
SRCS_BIN_TEST     = FileList[ 'src/ddbencode/*.c', 'src/test/*.c', 'vendor/cobject/src/cobject/*.c', 'vendor/uctest/src/uctest/*.c' ]

CFLAGS            = '-ggdb --std=c99 -W -Wall -Wno-unused-parameter -Iinclude -Ivendor/cobject/include -Ivendor/uctest/include'
LDFLAGS_BIN_TEST  = ''
LDFLAGS_LIB       = '-dynamiclib'

CC                = 'gcc'

### stuff you don't need to care about

require 'rake/clean'

OBJS_LIB       = SRCS_LIB.ext('o')
OBJS_BIN_TEST  = SRCS_BIN_TEST.ext('o')

CLEAN.include '**/*.o'
CLOBBER.include(TARGET_LIB, TARGET_BIN_TEST)

### tasks

task :default => [ :build, :test ]

task :build => [ TARGET_BIN_TEST, TARGET_LIB ]

task :test => [ TARGET_BIN_TEST ] do
  sh "echo ; ./#{TARGET_BIN_TEST}"
end

task :fetch_dependencies do
  # Make vendor dir
  FileUtils.mkdir('vendor') unless File.directory?('vendor')

  # Get cobject
  unless File.directory?('vendor/cobject')
    puts "=== Fetching cobject..."
    system('hg', 'clone', 'http://projects.stoneship.org/hg/shared/cobject', 'vendor/cobject')
    puts '=== Fetching cobject: done.'
  end

  # Get uctest
  unless File.directory?('vendor/uctest')
    puts "=== Fetching uctest..."
    system('hg', 'clone', 'http://projects.stoneship.org/hg/shared/uctest', 'vendor/uctest')
    puts '=== Fetching uctest: done.'
  end
end

### rules

rule '.o' => [ '.c' ] do |t|
  puts "CC #{t.source}"
  sh "#{CC} -c #{CFLAGS} -o #{t.name} #{t.source}"
end

file TARGET_BIN_TEST => OBJS_BIN_TEST do
  puts "LD #{TARGET_BIN_TEST}"
  sh "#{CC} #{CFLAGS} #{LDFLAGS_BIN_TEST} -o #{TARGET_BIN_TEST} #{OBJS_BIN_TEST}"
end

file TARGET_LIB => OBJS_LIB do
  puts "LD #{TARGET_LIB}"
  sh "#{CC} #{CFLAGS} #{LDFLAGS_LIB} -o #{TARGET_LIB} #{OBJS_LIB}"
end
