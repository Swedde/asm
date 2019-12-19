.name       "Batman"
.comment    "This city needs me"

loop:
        sti r09, %:live, %10000000000000000000
live:
        live %0
        ld 0, r2
        zjmp   %:loop
as:
