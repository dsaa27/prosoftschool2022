#!/usr/bin/env -iS bash --noprofile  --

declare -A tests

tests['commandcenter']=commandcenter_test
tests['serialization']=ser_test
tests['encoding']=message_encoder_test
tests['encoding/mirr']=mirr_test
tests['encoding/mul41']=mul41_test
tests['encoding/rot3']=rot3_test

for tdir in "${!tests[@]}"; do
    make -C $tdir && \
    ./$tdir/${tests[$tdir]}
done
