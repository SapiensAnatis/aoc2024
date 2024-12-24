i=1
end=20001
while [ $i -le $end ]; do
    clear
    echo $i
    cat ../cmake-build-debug/day15/$i.txt

    read -rsn 1 t
    case $t in
        C) i=$(($i+1)) ;; # right
        D) i=$(($i-1)) ;; # left
    esac
done
