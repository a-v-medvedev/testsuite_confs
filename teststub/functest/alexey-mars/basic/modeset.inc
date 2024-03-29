#!/bin/bash
#
#   This file is part of massivetest.
#
#   Massivetest is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Foobar is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
#
#


function set_specific_params() {
    local MODE=$1
    local SUBMODE=$2
    case "$SUBMODE" in
        base)
            ;;
        always)
            export MASSIVETEST_AUX_ARGS="-mode always"
            ;;
        never)
            export MASSIVETEST_AUX_ARGS="-mode never"
            ;;

        rand50)
            export MASSIVETEST_AUX_ARGS="-mode rand50"
            ;;

        *) fatal "Unknown submode: $SUBMODE"
            ;;
    esac

    case "$MODE" in
          base)
              ;;
          T)
              export MASSIVETEST_AUX_ARGS="$MASSIVETEST_AUX_ARGS -code T"
              ;;
          A)
              export MASSIVETEST_AUX_ARGS="$MASSIVETEST_AUX_ARGS -code A"
              ;;
          C)
              export MASSIVETEST_AUX_ARGS="$MASSIVETEST_AUX_ARGS -code C"
              ;;
          E)
              export MASSIVETEST_AUX_ARGS="$MASSIVETEST_AUX_ARGS -code E"
              ;;
          *) fatal "Unknown mode: $MODE"
             ;;
    esac
}
