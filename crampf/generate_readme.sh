#!/bin/bash

cat <<-EOF
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*                  CRAMPF Random Audio Mp3 Player Frontend                     *
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-



OVERVIEW

	Crampf is a console based mp3-player frontend with a ``vi-like''
	interface.



INSTALL

	Please see INSTALL for a quick installation guide.



DOCUMENTATION

	The program should be quite self-explanatory. For commandline parameters
	check `--help', to see the current hotkey-mappings press `h' during
	playback and `:help' to see all available commands. For a detailed help
	on each command enter `:help <commandname>'.
	For configuring the default behavior create a file $HOME/.crampfrc
	you may use any commands in this file which you would otherwise enter in
	the `:' mode.



BUGREPORTS

	I would be very happy to see any kind of (detailed) bugreports,
	feature-wishes or whatever. Just mail them to Kevin Loos <logic@tzi.org>.



ONLINE HELP

The following documentation is automatically generated from the online help.
It is meant to give an feature overview without the need to compile the binary.


crampf commandline usage:

EOF

sed -ne '/case .h.:/,/exit(0);/{
	    /".*"/{
		/VERSION/d
		s/^[^"]*"//
		s/\\n".*//
		s/\\"/"/g
		s/\\t/	/g
		s/\\\\/\\/g
		p
	    }
	}' options.cc

cat <<-EOF



Default hotkeys:

Key:	Command:
EOF

sed -ne '/op->cmdmap."map/{
	    s/^[^"]*"map //
	    s/".*//
	    s/\\"/"/g
	    s/\\t/	/g
	    s/\\\\/\\/g
	    s/ /	/
	    /^\\0[0-9][0-9]/{
		s/\\040/<space>/
		s/\\012/<enter>/
		s/\\011/<tab>/
	    }
	    p
	}' options.cc

cat <<-EOF

The following three Keys are always available
and cannot be redefined by the user:
:	enter command mode
/	search mode
?	rsearch mode



List of build in commands:
EOF

for i in commands/*.cc ; do
    sed -ne '/::help( const std::string &s ) const/,/^}/{
		/".*"/{
		    s/^[^"]*"//
		    s/\\n".*//
		    /format: /{
			h
			s/.*//
			p
			p
			x
			/autocommand/{
			    x
			    s/.*/autocommand/
			    x
			}
		    }
		    s/\\"/"/g
		    s/\\t/	/g
		    s/\\\\/\\/g
		    x
		    /autocommand/{
			x
			/%s/{
			    a\
'"`sed -ne '/autocmdmap\.newEvent( *"/{
	       s/^[^"]*"//
	       s/" *, *"/	/
	       s/".*/\\\\/
	       p
	   }' *.[ch][ch] */*.[ch][ch] */*/*.[ch][ch] */*/*/*.[ch][ch] 2>/dev/null`"'
			    
			    d
			}
			p
			d
		    }
		    x
		    p
		}
	    }' $i
done
