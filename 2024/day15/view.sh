i=1
i=1308
end=20001
while [ $i -le $end ]; do
    clear
    echo $i
    cat ../cmake-build-debug/day15/$i.txt

    read -rsn 1 t
    case $t in
        C) i=$(($i+1)) ;; # right arrow key
        D) i=$(($i-1)) ;; # left arrow key
    esac
done
