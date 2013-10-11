clear
sh ./clearImages
rm a.out
rm main.exe
gcc -pthread main.c -lm
cp a.out main.exe
#python main_ui.py &
./main.exe -t
#./main.exe -i
./main.exe -r
#sh ./buildImages
