:: ---------------------------------------------------------------------
:: COMPILERS COURSE - SCRIPT                                           -
:: SCRIPT A22 - CST8152 - Fall 2023                                    -
:: ---------------------------------------------------------------------

CLS
SET COMPILER=Compiler.exe

SET FILE1=INPUT0_Empty
SET FILE2=INPUT1_Hello
SET FILE3=INPUT2_Volume
SET FILE4=INPUT3_Factorial
SET FILE5=INPUT4_Datatypes
SET FILE6=INPUT5_General

SET ASSIGNMENT=A22
SET EXTENSION=amb
SET OUTPUT=out
SET ERROR=err

SET PARAM=s

:: ---------------------------------------------------------------------
:: Begin of Tests (A22 - F23) ------------------------------------------
:: ---------------------------------------------------------------------

@echo off

@echo off
echo "=---------------------------------------------------------="
echo "||          COMPILERS - ALGONQUIN COLLEGE (F23)          ||"
echo "|=-------------------------------------------------------=|"
echo "||                                                       ||"
echo "||                        _-_.                           ||"
echo "||	               _-',^. `-_.                        ||"
echo "||	            ._-' ,'   `.   `-_                    ||"
echo "||	   	   !`-_._________`-':::                   ||"
echo "||	           !   /\        /\::::                   ||"
echo "||	           ;  /  \      /..\:::                   ||"
echo "||	           ! /    \    /....\::                   ||"
echo "||	           !/      \  /......\:                   ||"
echo "||		   ;--.___. \/_.__.--;;                   ||"
echo "||	            '-_    `:!;;;;;;;'                    ||"
echo "||		  	`-_, :!;;;''                      ||"
echo "||	        	   `-!'                           ||"
echo "||                                                       ||"
echo "||     _____    __    __     _____     _____  __ __      ||"
echo "||    /\___/\  /_/\  /\_\  /\  __/\  /\_____\/_/\__/\    ||"
echo "||   / / _ \ \ ) ) \/ ( (  ) )(_ ) )( (_____/) ) ) ) )   ||"
echo "||   \ \(_)/ //_/ \  / \_\/ / __/ /  \ \__\ /_/ /_/_/    ||"
echo "||  / / _ \ \\ \ \\// / /\ \  _\ \  / /__/_\ \ \ \ \     ||"
echo "||  ( (_( )_) ))_) )( (_(  ) )(__) )( (_____\)_) ) \ \   ||"
echo "||   \/_/ \_\/ \_\/  \/_/  \/____\/  \/_____/\_\/ \_\/   ||"
echo "||                                                       ||"
echo "| =-----------------------------------------------------= |"
echo "=--------------------------------------------------------="

ECHO "[SCANNER SCRIPT .........................]"
ECHO "                                   "

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A22 - F23) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %FILE1%.%EXTENSION%	> %FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE2%.%EXTENSION%	> %FILE2%-%ASSIGNMENT%.%OUTPUT%	2> %FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE3%.%EXTENSION%	> %FILE3%-%ASSIGNMENT%.%OUTPUT%	2> %FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE4%.%EXTENSION%	> %FILE4%-%ASSIGNMENT%.%OUTPUT%	2> %FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE5%.%EXTENSION%	> %FILE5%-%ASSIGNMENT%.%OUTPUT%	2> %FILE5%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> %FILE6%-%ASSIGNMENT%.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: ---------------------------------------------------------------------
:: End of Tests (A22 - F23) --------------------------------------------
:: ---------------------------------------------------------------------
