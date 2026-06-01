#!/bin/dash

fifo="/tmp/dwmbar.fifo"
[ -e "$fifo" ] && rm "$fifo"
mkfifo "$fifo"
exec 3<>"$fifo"

trap 'pkill -P $$ 2>/dev/null; rm "$fifo" 2>/dev/null; exit' EXIT TERM INT
trap 'pkill -P $$' EXIT


pkill -f "pactl subscribe" 2>/dev/null
pkill -f "playerctl status" 2>/dev/null


(
    format_key() {
        case "$1" in
            us) echo "En" ;;
            ua) echo "Ua" ;;
            *) echo "E" ;;
        esac
    }

    init_key=$(xkb-switch -p 2>/dev/null)
    echo "KEY$(format_key "$init_key")" >&3

    xkb-switch -W 2>/dev/null | while read -r curr_key; do
        echo "KEY$(format_key "$curr_key")" >&3
    done
) &

(
    get_vol() {
        if pactl get-sink-mute @DEFAULT_SINK@ | grep -q 'yes'; then
            echo "VOL♬˖.✦M" >&3
        else
            vol=$(pactl get-sink-volume @DEFAULT_SINK@ | awk '{print $5}')
            echo "VOL♬˖°$vol" >&3
        fi
    }
    get_vol
    pactl subscribe | while read -r event; do
        case "$event" in *'sink'*) get_vol ;; esac
    done
) &

(
    while :; do
        if [ -d /sys/class/power_supply/BAT1 ]; then
            read -r cap < /sys/class/power_supply/BAT1/capacity
            read -r stat < /sys/class/power_supply/BAT1/status
            if [ "$stat" = "Charging" ]; then bat="BAT✿✦${cap}%"
            elif [ "$cap" -eq 100 ]; then bat="BAT˚✿˖°"
            else bat="BAT✿ ${cap}%"; fi
            echo "$bat" >&3
        fi
        echo "DAT$(date +'%m.%d %H:%M')" >&3
        sleep 60
    done
) &

(
    moc_info=$(mocp -i 2>/dev/null)
    state=$(echo "$moc_info" | awk '/^State:/{print $2}')
    
    if [ "$state" = "PLAY" ]; then
        playing=$(echo "$moc_info" | awk -F'/' '/^File:/{sub(/\.mp3$/, "", $NF); print $NF}')
        
        echo "$playing" > /tmp/dwm_music
        echo "MUS$playing" >&3
    else
        echo "✿ Enjoying the Silence ✿" > /tmp/dwm_music
        echo "MUS✿ Enjoying the Silence ✿" >&3
    fi
) &

while read -r line <&3; do
    case "$line" in
        DAT*) date="${line#???}" ;;
        VOL*) volume="${line#???}" ;;
        BAT*) battery="${line#???}" ;;
        KEY*) key="${line#???}" ;;
        MUS*) ;;
    esac
    xsetroot -name "|  $key  |  $volume  |  $battery  |  $date  "
done
