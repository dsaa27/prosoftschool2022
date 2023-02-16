#!/usr/bin/env -iS bash --norc --

declare -A tests

tests['commandcenter']=commandcenter_test
tests['serialization']=ser_test
tests['encoder']=message_encoder_test
tests['encoder/mirr']=mirr_test
tests['encoder/mul41']=mul41_test
tests['encoder/rot3']=rot3_test

for tdir in "${!tests[@]}";do
    make -C $tdir && \
    ./$tdir/${tests[$tdir]}
done
