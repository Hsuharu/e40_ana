#!/bin/bash

#_____________________________
#    RUN MANAGER for DST
#  AUTHOR: Yoshiyuki NAKADA
#      July 24, 2028
#_____________________________


APP_PATH=$(readlink -f $0)
APP_DIR=$(dirname $APP_PATH)

#__________________________________________________

QUIET=0
while getopts ":q" opt; do
    case $opt in
	q ) QUIET=1 ;;
	* ) echo "ERROR: Invalid option"; exit 1 ;;
    esac
done

shift $(($OPTIND - 1))

#__________________________________________________

if [ $# -ne 1 ]; then
    echo "USAGE: $0 [runlist]"
    exit 0
fi

if ! [ -e "$1" ]; then
    echo "ERROR: No such file > $1"
    exit 1
fi

runlist=$1

tmp=$(basename $runlist)
label=${tmp%.*}

#__________________________________________________

LOG_DIR=$APP_DIR/log
if ! [ -e $LOG_DIR ]; then
    mkdir $LOG_DIR
fi

PREFETCH_DIR=$APP_DIR/prefetch
if ! [ -e $PREFETCH_DIR ]; then
    mkdir $PREFETCH_DIR
fi

mainlog=$LOG_DIR/$label.log
if [ -e $mainlog ]; then
    rm -f $mainlog
fi
echo $mainlog >> $mainlog
date >> $mainlog

work=""
bin=""
conf=""
rootin=""
rootout=""
runid=()
conff=()			# conf file array

#__________________________________________________

while read line; do

    if [ -z "$line" -o "${line:0:1}" = '#' ]; then
	continue
    elif [ "${line:0:5}" = 'work:' ]; then
	tmp=( $line )
	work=${tmp[1]}
	continue
    elif [ "${line:0:4}" = 'bin:' ]; then
	tmp=( $line )
	bin=${tmp[1]}
	continue
    elif [ "${line:0:5}" = 'conf:' ]; then
	tmp=( $line )
	conf=${tmp[1]}
	continue
    elif [ "${line:0:7}" = 'rootin:' ]; then
	tmp=( $line )
	rootin=${tmp[1]}
	continue
    elif [ "${line:0:8}" = 'rootout:' ]; then
	tmp=( $line )
	rootout=${tmp[1]}
	continue
    fi

    words=( $line )
    for item in ${words[@]}; do

	if [ "${item:0:1}" == '#' ]; then
	    break
	fi

	expr $item + 1 >/dev/null 2>&1
	if [ $? -lt 2 ]; then
	    tmp=$(( 10#$item ))
	    runid+=( $(printf %05d $tmp) )
	fi
    done
    
done < $runlist

#__________________________________________________

if [ -z "$work" ] || ! [ -d "$work" ]; then
    echo "ERROR: Invalid file declaration [work: $work]" | tee $mainlog
    exit 1
fi

#__________________________________________________

echo "> cd $work" >> $mainlog
cd $work
if [ $? -eq 1 ]; then
    exit 1
fi

if ! [ -x "$bin" ]; then
    if [ -z "$bin" ]; then bin="null"; fi
    echo "ERROR: Invalid file declaration [bin: $bin]" | tee $mainlog
    exit 1
fi

if [ -d "$conf" ]; then
    for id in ${runid[@]}; do
	tmpconf="$conf/analyzer_${id}.conf"
	if ! [ -r "$tmpconf" ]; then
	    echo "ERROR: Cannot access file >> $tmpconf" | tee $mainlog
	    exit 1
	fi
	conff+=( "$tmpconf" )
    done
elif [ -r "$conf" ]; then
    for id in ${runid[@]}; do
	conff+=( "$conf" )
    done
else
    if [ -z "$conf" ]; then conf="null"; fi
    echo "ERROR: Invalid file declaration [conf: $conf]" | tee $mainlog
    exit 1
fi

if ! [ -d "$rootin" ]; then
    if [ -z "$rootin" ]; then rootin="null"; fi
    echo "ERROR: Invalid file declaration [rootin: $rootin]" | tee $mainlog
    exit 1
fi

if ! [ -d "$rootout" ]; then
    if [ -z "$rootout" ]; then rootout="null"; fi
    echo "ERROR: Invalid file declaration [rootout: $rootout]" | tee $mainlog
    exit 1
fi

#__________________________________________________

element=()
basebin=$(basename $bin)
if [ "$basebin" = "DstPiKAna" ]; then
    element=( "KuramaTracking" "K18Tracking" "Hodoscope" "Easiroc" )
elif [ "$basebin" = "DstKuramaHodoscope" ]; then
    element=( "KuramaTracking" "Hodoscope" )
else
    echo "ERROR: Unsupported DST [$basebin]" | tee $mainlog
    exit 1
fi

#__________________________________________________

echo "> cd $work/$rootin" >> $mainlog
cd $work/$rootin
if [ $? -eq 1 ]; then
    exit 1
fi

fl_exit=0
for id in ${runid[@]}; do
    for item in ${element[@]}; do
	target="run${id}_${item}.root"
	if ! [ -r "$target" ]; then
	    echo "ERROR: Unreachable ROOT input file [$work/$rootin/$target]" | tee $mainlog
	    fl_exit=1
	fi
    done
done

if [ $fl_exit -eq 1 ]; then
    exit 1
fi

#__________________________________________________

echo "> cd $APP_DIR" >> $mainlog
cd $APP_DIR
if [ $? -eq 1 ]; then
    exit 1
fi

if ! [ -e $LOGDIR ]; then
    echo "> mkdir $LOG_DIR" >> $mainlog
    mkdir $LOG_DIR
fi

prefetch=()

if ! [ -e $PREFETCH_DIR ]; then
    echo "> mkdir $PREFETCH_DIR"
    mkdir $PREFETCH_DIR
else
    for id in ${runid[@]}; do
	path=$(readlink -f $PREFETCH_DIR/${label}_run${id}_${basebin}.pf)
	if [ -e $path ]; then
	    echo "> rm -f $path" >> $mainlog
	    rm -f $path
	fi
	for item in ${element[@]}; do
	    dir="${work}/${rootin}"
	    echo $(readlink -f ${dir}/run${id}_${item}.root) >> $path
	done
	prefetch+=( $path )
    done
fi

#__________________________________________________

echo "> cd $work" >> $mainlog
cd $work
if [ $? -eq 1 ]; then
    exit 1
fi

log=()
out=()
pid=()

index=0
for id in ${runid[@]}; do
    tmplog="$LOG_DIR/${label}_run${id}_${basebin}.log"
    tmpout="$LOG_DIR/${label}_run${id}_${basebin}.out"
    if [ -e $tmplog ]; then
	echo "> rm -f $tmplog" >> $mainlog
	rm -f $tmplog
    fi
    if [ -e $tmpout ]; then
	echo "> rm -f $tmpout" >> $mainlog
	rm -f $tmpout
    fi
    command_prefetch="prefetch (${prefetch[$index]})"
    inpath=()
    for item in ${element[@]}; do
	inpath+=( $(readlink -f $work/$rootin/run${id}_${item}.root) )
    done
    outpath=$(readlink -f $work/$rootout/run${id}_${basebin}.root)
    start=$( date )
    bsub -q s -o $tmplog -a "$command_prefetch" $work/$bin $work/${conff[$index]} ${inpath[@]} $outpath > $tmpout &
    pid+=( $! )
    log+=( $tmplog )
    out+=( $tmpout )
    echo "> bsub -q s -o $tmplog -a $command_prefetch $work/$bin $work/${conff[$index]} ${inpath[@]} $outpath > $tmpout &" >> $mainlog
    echo "key: $id"                            >> $mainlog
    echo "-- log:      $tmplog"                >> $mainlog
    echo "-- out:      $tmpout"                >> $mainlog
    echo "-- prefetch: ${prefetch[$index]}"    >> $mainlog
    echo "-- bin:      $work/$bin"             >> $mainlog
    echo "-- conf:     $work/${conff[$index]}" >> $mainlog
    echo "-- rootin:   ${inpath[@]}"           >> $mainlog
    echo "-- rootout:  $outpath"               >> $mainlog
    echo "-- start:    $start"                 >> $mainlog
    echo "-- pid:      ${pid[$index]}"         >> $mainlog
    index=$(( $index + 1 ))
done

#__________________________________________________

index=0
for item in ${pid[@]}; do
    wait $item
    if [ $? -ne 0 ]; then
	echo "ERROR: bsub returned false [key: ${runid[index]}]" | tee $mainlog
    else
	while read line; do
	      words=( $line )
	      if [ "${words[0]}" = "Job" \
				 -a "${words[2]}" = "is" \
				 -a "${words[3]}" = "submitted" \
				 -a "${words[4]}" = "to" \
				 -a "${words[5]}" = "queue" ]; then
		  buff=${words[1]##<}
		  jid[$index]=${buff%%>}
		  echo "job id [${runid[$index]}]: ${jid[$index]}" >> $mainlog
	      fi
	done < ${out[index]}
    fi
    index=$(( $index + 1 ))
done

#__________________________________________________

fl_done=0
success=0

stat=()

while : ; do
    index=0
    for id in ${runid[@]}; do
	if [ ${#jid[$index]} -ne 0 ]; then
	    while read tmpjid tmpuid tmpstat \
		       tmpqueue tmphost1 tmphost2 tmpjname \
		       tmptime; do
		if [ "$tmpjid" = "${jid[$index]}" ]; then
		    case "$tmpstat" in
			"PEND" ) stat[$index]=0 ;;
			"RUN"  ) stat[$index]=1 ;;
			"DONE" )
			    if [ ${stat[$index]} -lt 2 ]; then
				fl_done=$(($fl_done + 1))
				success=$(($success + 1))
				finish=$( date )
				echo "done [$id]: $finish" >> $mainlog
			    fi
			    stat[$index]=2
			    ;;
			"EXIT" )
			    if [ ${stat[$index]} -lt 2 ]; then
				fl_done=$(($fl_done + 1));
				finish=$( date )
				echo "exit [$id]: $finish" >> $mainlog
			    fi
			    stat[$index]=3
			    ;;
			* )
			    echo "ERROR: Unknow status was detected [key: $id]" | tee $mainlog
			    stat[$index]=-1 ;;
		    esac
		fi
	    done < <(bjobs ${jid[$index]})
	fi
	index=$(($index + 1))
    done
    if [ $QUIET -eq 0 ]; then
	prog=""
	for item in ${stat[@]}; do
	    case $item in
		0 ) prog="${prog}." ;;
		1 ) prog="${prog}:" ;;
		2 ) prog="${prog}!" ;;
		3 ) prog="${prog}x" ;;
		4 ) prog="${prog}?" ;;
		* ) prog="${prog}?" ;;
	    esac
	done
	echo -en "executing... [$prog] $fl_done/${#jid[@]}\r"
    fi
    if [ ${#jid[@]} -eq $fl_done ]; then break; fi
done

if [ $QUIET -eq 0 ]; then echo -en "\n"; fi

index=0
for dummy in ${runid[@]}; do
    echo "> rm -f ${out[$index]}" >> $mainlog
    rm -f ${out[$index]}
    echo "> rm -f ${prefetch[$index]}" >> $mainlog
    rm -f ${prefetch[$index]}
    if [ ${stat[$index]} -eq 2 ]; then
	echo "> rm -f ${log[$index]}" >> $mainlog
	rm -f ${log[$index]}
    fi
    index=$(($index + 1))
done

if [ ${#runid[@]} -eq $success ]; then
    rm -f $mainlog
fi
