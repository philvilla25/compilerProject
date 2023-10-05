#************************************************************
#* COMPILERS COURSE - Algonquin College
#* Code version: Fall, 2023
#* Author: TO_DO
#* Professors: Paulo Sousa
#************************************************************
#=---------------------------------------=
#|  COMPILERS - ALGONQUIN COLLEGE (F23)  |
#=---------------------------------------=
#|              ....                     |
#|          ........::.::::::.           |
#|        .:........::.:^^^~~~:          |
#|        :^^::::::^^^::^!7??7~^.        |
#|       .:^~~^!77777~~7?YY?7??7^.       |
#|       :.^~!??!^::::^^~!?5PY??!~.      |
#|       ~!!7J~.:::^^^^~!!~~?G5J?~       |
#|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |
#|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |
#|       .~77..    . .~^:^^^~7?:         |
#|       .^!^~:::.:^!7?~^~!77J:          |
#|        ^^!Y~^^^^~?YJ77??7JJ^          |
#|       .^7J?~^~~^~7??7??7JY?~:         |
#|        ::^^~^7?!^~~!7???J?J7~:.       |
#|         ^~~!.^7YPPPP5Y?7J7777~.       |
#|        ..:~..:^!JPP5YJ?!777!^.        |
#| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |
#|     A   M   M   BBBBB    EEEEE  RRRR  |
#|    / \  MM MM  B     B  E      R   R  |
#|   |   | M M M  BBBBB    EEEE   RRRR   |
#|   |   | M   M  B     B  E      R  R   |
#|   |   | M   M   BBBBB    EEEEE  R   R |
#=---------------------------------------=

cmake_minimum_required (VERSION 3.8)

project ("Compiler")

# Add source to this project's executable: check name and dependences
add_executable (Compiler
	"Compilers.h"	"Compilers.c"
	"Reader.h"		"Reader.c"		"MainReader.c"
	#"Scanner.h"		"Scanner.c"		"MainScanner.c"
	#"Parser.h"		"Parser.c"		"MainParser.c"
	# TO_DO: Add A22 (Scanner) and A32 (Parser)
)

# TO_DO: Add tests and install targets if needed.
