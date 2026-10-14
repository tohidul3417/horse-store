// 0x6080604052348015600f57600080fd5b5060ac8061001e6000396000f3fe6080604052348015600f57600080fd5b506004361060325760003560e01c8063cdfead2e146037578063e026c017146049575b600080fd5b60476042366004605e565b600055565b005b60005460405190815260200160405180910390f35b600060208284031215606f57600080fd5b503591905056fea2646970667358221220f4859045d69de32a90a3c6a286b094585557098ee6c9ef781043b3d2072dd79164736f6c63430008140033

// 3 Sections:
//   1. Contract Creation
//   2. Runtime
//   3. Metadata

// 1. Contract Creation Code
// Set the free memory pointer to the memory location 0x80
[00]	PUSH1	80
[02]	PUSH1	40 // Stack: [0x40, 0x80]
[04]	MSTORE // Memory: [...0...0...0x80]

// Check whether any value (msg.value) is sent. Sent ? REVERT : Jump to PC 0f
[05]	CALLVALUE // Stack: [msg.value]
[06]	DUP1 // Stack: [msg.value, msg.value]
[07]	ISZERO // Stack: [isZero, msg.value]
[08]	PUSH1	0f // Stack: [0x0f, isZero, msg.value]
[0a]	JUMPI // Jump to PC 0f if isZero. Stack: [msg.value]
[0b]	PUSH1	00 // [0x00, msg.value]
[0d]	DUP1 // [0x00, 0x00, msg.value]
[0e]	REVERT //

// No value is sent then the next instruction will be executed
[0f]	JUMPDEST // Stack [msg.value]
[10]	POP   // Stack []
[11]	PUSH1	ac
[13]	DUP1
[14]	PUSH2	001e
[17]	PUSH1	00 // Stack: [00, 1e, ac, ac]
[19]	CODECOPY // copy code from from PC 1e upto 1e+ac(0xca)
[1a]	PUSH1	00 // Stack: [0x00, 0xac]
[1c]	RETURN //
[1d]	INVALID




// 2. Runtime code
// Entry point of all calls
// Free memory pointer
[1e]	PUSH1	80
[20]	PUSH1	40  // Stack: [0x40, 0x80]
[22]	MSTORE

// Checking if Value is sent. If sent revert.
[23]	CALLVALUE   // Stack: [msg.value]
[24]	DUP1        // Stack: [msg.value, msg.value]
[25]	ISZERO      // Stack: [1, msg.value]
[26]	PUSH1	0f  // Stack: [0x0f, 1, msg.value]
[28]	JUMPI       // Jump into PC offset 0x0f as b is 1. Stack [msg.value]
[29]	PUSH1	00  // if not zero: Stack: [0x00, mgs.value]
[2b]	DUP1        // [0x00, 0x00, msg.value]
[2c]	REVERT      // Revert. Stack [msg.value]

//
[2d]	JUMPDEST // Runtime Code PC: 0x0f.   Stack [msg.value]
[2e]	POP      // Stack: []
[2f]	PUSH1	04 // Stack: [0x04]
[31]	CALLDATASIZE // Stack: [calldatasize, 0x04]
[32]	LT //   Calldata size less than 0x04? then [1] otherwise [0]
[33]	PUSH1	32  // Stack [0x32, Lt_resutl]
[35]	JUMPI       // if Calldata is too small (Lt_result is 1) jump to runtime code PC 0x32(50)

// Calldata
[36]	PUSH1	00           // Stack: [0x00]
[38]	CALLDATALOAD        // Stack: [first 32 bytes of calldata]
[39]	PUSH1	e0
[3b]	SHR                 // Stack: [fn selector]

// is fn selector == cdfead2e(updateHorseNumber(uint256))
[3c]	DUP1                // Stack: [fn selector]
[3d]	PUSH4	cdfead2e  // Stack: [cdfead2e(updateHorseNumber(uint256)), fn selector, fn selector]
[42]	EQ                  // Matched? 1 Not matched 0
[43]	PUSH1	37          // Stack: [0x37, matchResult, fn selector]
[45]	JUMPI               // so if fn selector is cdfead2e then jump 🚀 to runtime code instruction offset 0x37   stack now: stack [fn selector]

// is fn selector == e026c017(readNumberOfHorses())?
[46]	DUP1                // Stack now: [fn selector, fn selector]
[47]	PUSH4	e026c017    // Stack now: [e026c017, fn selector, fn selector]
[4c]	EQ                  // Stack now: [selector match result, fn selector]
[4d]	PUSH1	49         // Stack now: [0x49, selector match result, fn selector]
[4f]	JUMPI              // Jump 🚀 to runtime PC ox49(0x67 here) if matched. Stack: [fn selector]

// When calldata is emtpy or less than 4 bytes in size
[50]	JUMPDEST        // In case calldata is empty or less than 4 byte
[51]	PUSH1	00
[53]	DUP1            // Stack: [0x00, 0x00]
[54]	REVERT          // Stack: []


// updateHorseNumber(uint256) jumpdest 1
[55]	JUMPDEST         // Jump here for if fn selector is cdfead2e (updateHorseNumber(uint256)). Stack Now: [cdfead2e]
[56]	PUSH1	47
[58]	PUSH1	42      // Stack Now: [0x42, 0x47, 0xcdfead2e]
[5a]	CALLDATASIZE    // Stack Now: [calldatasize, 0x42, 0x47, 0xcdfead2e]
[5b]	PUSH1	04
[5d]	PUSH1	5e      // Stack Now: [0x5e, 0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[5f]	JUMP            // 🚀JUMP to  runtime code PC 0x5e (here 0x7c,)                         Stack Now: [0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]

// updateHorseNumber(uint256) jumpdest 4
[60]	JUMPDEST // Stack Now: [calldata[0x04:0x04+32], 0x47, 0xcdfead2e]
[61]	PUSH1	00  // S: [0x00, calldata[0x04:0x04+32], 0x47, 0xcdfead2e]
[63]	SSTORE      // Store calldata[0x04:0x04+32] into storage location 0x00                  Stack Now: [0x47, 0xcdfead2e]
[64]	JUMP // Jump 🚀 to 0x47 (0x65)  Stack Now: [0xcdfead2e]

[65]	JUMPDEST    // Stack Now: [0xcdfead2e]
[66]	STOP        // Exit!✅

// readNumberOfHorses() only jumpdest
[67]	JUMPDEST
[68]	PUSH1	00   // Stack: [0x00, fn selector]
[6a]	SLOAD        // Stack: [numberOfHorses, fn selector]
[6b]	PUSH1	40   // Stack: [0x40, numberOfHorses, fn selector]
[6d]	MLOAD        // Stack: [0x80, numberOfHorses, fn selector]
[6e]	SWAP1        // Stack: [numberOfHorses, 0x80, fn selector]
[6f]	DUP2         // Stack: [0x80, numberOfHorses, 0x80, fn selector]
[70]	MSTORE       // S: [0x80, fn s]
[71]	PUSH1	20   // S: [0x20, 0x80, fn s]
[73]	ADD          // S: [0xa0, fn s]
[74]	PUSH1	40   // S: [0x40, 0xa0, fn s]
[76]	MLOAD        // S: [0x80, 0xa0, fn s]
[77]	DUP1         // S: [0x80, 0x80, 0xa0, fn s]
[78]	SWAP2        // S: [0xa0, 0x80, 0x80, fn s]
[79]	SUB          // S: [0x20, 0x80, fn s]
[7a]	SWAP1        // S: [0x80, 0x20, fn s]
[7b]	RETURN       // S: [fn s] EXECUTION is HALTED

// updateHorseNumber(uint256) jumpdest 2
[7c]	JUMPDEST        // Stack Now: [0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[7d]	PUSH1	00      // Stack Now: [0x00, 0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[7f]	PUSH1	20       // Stack Now: [0x20, 0x00, 0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[81]	DUP3            // Stack Now: [0x04, 0x20, 0x00, 0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[82]	DUP5      // S: [calldatasize, 0x04, 0x20, 0x00, 0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[83]	SUB       // S: [subResult, 0x20, 0x00, 0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[84]	SLT       // S: [subResult < 0x20, 0x00, 0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[85]	ISZERO    // S: [zero?, 0x00, 0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[86]	PUSH1	6f  // S: [6f, zero?, 0x00, 0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[88]	JUMPI       // S: jump🚀 to 0x6f(0x8d) if zero which means calldata is not less than 32 bytse. Stack Now: [0x00, 0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]

// Revert if there is not enough calldata
[89]	PUSH1	00
[8b]	DUP1
[8c]	REVERT

// updateHorseNumber(uint256) jumpdest 3
[8d]	JUMPDEST     // Stack Now: [0x00, 0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[8e]	POP          // Stack Now: [0x04, calldatasize, 0x42, 0x47, 0xcdfead2e]
[8f]	CALLDATALOAD // Stack Now: [calldata[0x04:0x04+32], calldatasize, 0x42, 0x47, 0xcdfead2e]
[90]	SWAP2        // Stack Now: [0x42, calldatasize, calldata[0x04:0x04+32], 0x47, 0xcdfead2e]
[91]	SWAP1        // Stack Now: [calldatasize, 0x42, calldata[0x04:0x04+32], 0x47, 0xcdfead2e]
[92]	POP          // Stack Now: [0x42, calldata[0x04:0x04+32], 0x47, 0xcdfead2e]
[93]	JUMP         // Jump 🚀 to 0x42(0x60) (Stack Now: [calldata[0x04:0x04+32], 0x47, 0xcdfead2e]
[94]	INVALID




// ---- 3. Metadata ----
[95]	LOG2
[96]	PUSH5	6970667358
[9c]	INVALID
[9d]	SLT
[9e]	KECCAK256
[9f]	DELEGATECALL
[a0]	DUP6
[a1]	SWAP1
[a2]	GASLIMIT
[a3]	INVALID
[a4]	SWAP14
[a5]	INVALID
[a6]	INVALID
[a7]	SWAP1
[a8]	LOG3
[a9]	INVALID
[aa]	LOG2
[ab]	DUP7
[ac]	INVALID
[ad]	SWAP5
[ae]	PC
[af]	SSTORE
[b0]	JUMPI
[b1]	MULMOD
[b2]	DUP15
[b3]	INVALID
[b4]	INVALID
[b5]	INVALID
[b6]	PUSH25	1043b3d2072dd79164736f6c63430008140033
