#
#  [2019] Signet Lab - Programming for ICT
#
#  Authors Filippo Campagnaro and Michele Polese 
#

case `uname` in Darwin*) glibtoolize ;;
  *) libtoolize ;; esac
aclocal
autoconf
automake --add-missing
