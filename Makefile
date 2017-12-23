all: calendar file_reader http_get_server ls matrix stack temperature_converter text_finder tree turing_machine

clear: calendar_clear file_reader_clear http_get_server_clear ls_clear matrix_clear stack_clear temperature_converter_clear text_finder_clear tree_clear turing_machine_clear

calendar:
	cd calendar && make

calendar_clear:
	cd calendar && make clear

file_reader:
	cd file_reader && make

file_reader_clear:
	cd file_reader && make clear

http_get_server:
	echo "!!WARNING!!"
	echo "current server version is unstable and may fail"
	echo
	cd http_get_server && make

http_get_server_clear:
	cd http_get_server && make clear

ls:
	cd ls && make

ls_clear:
	cd ls && make clear

matrix:
	cd matrix && make

matrix_clear:
	cd matrix && make clear

stack:
	cd stack && make

stack_clear:
	cd stack && make clear

temperature_converter:
	cd temperature_converter && make

temperature_converter_clear:
	cd temperature_converter && make clear

text_finder:
	cd text_finder && make

text_finder_clear:
	cd text_finder && make clear

tree:
	cd tree && make

tree_clear:
	cd tree && make clear

turing_machine:
	cd turing_machine && make

turing_machine_clear:
	cd turing_machine && make clear
