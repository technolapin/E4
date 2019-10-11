mkdir target
mkdir vg_logs
gcc -g src/exercice_1_v1.c -o target/exo1v1.out
gcc -g src/exercice_1_v2.c -o target/exo1v2.out
gcc -g src/exercice_1_v3.c -o target/exo1v3.out
valgrind --tool=cachegrind ./target/exo1v1.out > vg_logs/exo1v1 2>&1
valgrind --tool=cachegrind ./target/exo1v2.out > vg_logs/exo1v2 2>&1
valgrind --tool=cachegrind ./target/exo1v3.out > vg_logs/exo1v3 2>&1
