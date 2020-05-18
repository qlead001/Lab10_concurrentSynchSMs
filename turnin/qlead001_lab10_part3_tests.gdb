# Test file for "Lab10_concurrentSynchSMs"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

setPINA 0xFF

test "Wait => PORTB[3:0]: 0000"
timeContinue 1
expectPORTB 0
checkResult

test "Wait => PORTB[3:0]: 0001"
timeContinue 300
expectPORTB 1
checkResult

test "Wait => PORTB[3:0]: 0010"
timeContinue 300
expectPORTB 2
checkResult

test "PINA2: 0 => PORTB[4:0]: 10010"
setPINA 0xFB
timeContinue 2
expectPORTB 0x12
checkResult

test "Wait => PORTB[4:0]: 00010"
timeContinue 2
expectPORTB 0x02
checkResult

test "Wait => PORTB[4:0]: 10010"
timeContinue 2
expectPORTB 0x12
checkResult

test "PINA2: 1 => PORTB[4:0]: 00010"
setPINA 0xFF
timeContinue 3
expectPORTB 0x02
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
