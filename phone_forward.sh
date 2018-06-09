prog=$1
oper=$2
numb=$3

# Sprawdzenie poprawności wejścia, jeśli pojawi się coś innego niż cyfry i znak > to error i exit
if cat $oper | grep -P '[^0-9>\s]' > /dev/null; then
    echo "ERROR - błąd pliku z przekierowaniami"
    exit
fi

# Uruchomienie programu
(echo "NEW base"; cat $oper; echo " ?$numb") | $prog > /dev/null 2> /dev/null
 
# Weryfikacja kodu wyjścia programu, jeśli program dał exit(1), to znaczy że coś poszło nie tak...
# Wtedy error i exit
if [ $? = 1 ]; then
    echo "ERROR - błąd wejścia"
    exit
fi

# Zapisanie wyniku dla zapytania ?
tab1=()
tab2=()
ind=0
for i in `(echo "NEW base"; cat $oper; echo " ?$numb") | $prog`; do
    tab1[$ind]=$i?
    tab2[$ind]=$i
    ((ind++))
done;

# Sprawdzenie poprawności znalezionych liczb
ind=0
for i in `(echo "NEW base"; cat $oper; echo " ${tab1[@]}") | $prog`; do
    if [ $i = $numb ]; then
        echo ${tab2[$ind]}
    fi;
    ((ind++))
done;