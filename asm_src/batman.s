.name  "Batman"#
.comment    "this city needs me"

loop:
        sti r01, %:live, %1
live:
        live %-0009,,,,
        ld %0, r2
        zjmp %:loop
