exec >commands.hh.new
echo '//                                                                '
echo '// One class for each command. doit method called by commandmap   '
echo '//                                                                '
echo '// THIS FILE IS AUTOMATICLY CREATED BY COMMANDS.SH                '
echo '// DONT EDIT!                                                     '
echo '//                                                                '
echo '                                                                  '
echo '#ifndef COMMANDS_HH                                               '
echo '#define COMMANDS_HH COMMANDS_HH                                   '
echo '                                                                  '
echo '#include <string>                                                 '
echo '#include "../command.hh"                                          '
echo '#include "../commandmap.hh"                                       '
echo '                                                                  '
ls -1 *.hh | sed s/^/'\#include \"'/ | sed s/$/'\"'/
echo '                                                                  '
echo '#endif                                                            '
echo '                                                                  '
if diff commands.hh commands.hh.new &>/dev/null ; then
  rm -f commands.hh.new
else
  mv -f commands.hh.new commands.hh 
fi
exit 0
