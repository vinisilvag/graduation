#!/bin/bash
if test -z $1 || test ! -f "$1"
    then echo 'Os dois primeiros parametros devem ser os arquivos C++ (ja compilados) a comparar saida.'
elif test -z $2 || test ! -f "$2"
    then echo 'Os dois primeiros parametros devem ser os arquivos C++ (ja compilados) a comparar saida.'
elif test -z $3 || test ! -f $3
    then echo 'O terceiro parametro deve ser o arquivo C++ (ja compilado) que gera entrada dado uma seed na linha de comando.'
else
    #make $1 $2 $3 || exit 1
    # a1, a2, gen
    for ((i = 1; ; i++)) do
	    ./$3 $i > in
	    ./$1 < in > "$1out"
	    ./$2 < in > "$2out2"
	    if (! cmp -s "$1out" "$2out2") then
		    echo "--> entrada:"
		    cat in
		    echo "--> saida1:"
		    cat "$1out"
		    echo "--> saida2:"
		    cat "$2out2"
		    break;
	    fi
	    echo $i
    done
fi
