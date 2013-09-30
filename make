clear
rm a.out
rm main.exe
gcc -pthread main.c -lm
cp a.out main.exe
./main.exe -t
#python main_ui.py &
./main.exe -r

