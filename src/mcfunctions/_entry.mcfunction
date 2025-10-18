data modify storage {0} args set value {}
data modify storage {0} global set value {}
data modify storage {0} stack set value []
data modify storage {0} memory set value [{1}]
scoreboard objectives add register dummy
scoreboard players set stackTop register 0
scoreboard objectives add const dummy
{2}
data modify storage {0} stack insert -1 value {}
function llvm2mc:main
data remove storage {0} stack[-1]