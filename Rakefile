### configuration

TARGET_BIN_TEST   = 'bencode_test'
TARGET_LIB        = 'bencode.dylib'

SRCS_LIB          = FileList[ 'src/bencode/*.c' ]
SRCS_BIN_TEST     = FileList[ 'src/bencode/*.c', 'src/test/*.c', 'vendor/uctest/src/uctest/*.c' ]

CFLAGS            = '--std=c99 -W -Wall -Wno-unused-parameter -Iinclude -Ivendor/uctest/include'
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

### rules

rule '.o' => [ '.c' ] do |t|
  sh "#{CC} -c #{CFLAGS} -o #{t.name} #{t.source}"
end

file TARGET_BIN_TEST => OBJS_BIN_TEST do
  sh "#{CC} #{CFLAGS} #{LDFLAGS_BIN_TEST} -o #{TARGET_BIN_TEST} #{OBJS_BIN_TEST}"
end

file TARGET_LIB => OBJS_LIB do
  sh "#{CC} #{CFLAGS} #{LDFLAGS_LIB} -o #{TARGET_LIB} #{OBJS_LIB}"
end
