# Project 1 ROBDD Generation

資訊工程系 二年級 乙班 張皓鈞 B11030202



## Build

Use CMake as build tool

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```



## Test Platform

![Screenshot 2023-09-21 at 7.39.03 PM](./assets/Screenshot 2023-09-21 at 7.39.03 PM.png)

### macOS

```
Darwin ip139-200.wlan.ntust.edu.tw 22.6.0 Darwin Kernel Version 22.6.0: Wed Jul  5 22:22:52 PDT 2023; root:xnu-8796.141.3~6/RELEASE_ARM64_T8103 arm64
```

### Apple Clang

```
Apple clang version 14.0.3 (clang-1403.0.22.14.1)
```

### Graphviz

```
dot - graphviz version 8.1.0 (20230707.0739)
```



## Test Case

### Case 1 (4 variables)

$$
f(p, q, r, s) = p \land q \land r \land s + p \land q \land \neg r \land s + p \land \neg q \land r \land s
$$

#### Input PLA

[examples/case7/input.pla](../../examples/case7/input.pla)

```pla
.i 4
.o 1
.ilb p q r s
.ob f
.p 3
1111 1
1101 1
1011 1
.e
```

#### Output DOT

```dot
digraph ROBDD{
        {rank=same 2}
        {rank=same 4}
        {rank=same 7}
        {rank=same 14}

        0[label=0, shape=box]
        1[label=1, shape=box]
        2[label="p"]
        4[label="q"]
        7[label="r"]
        14[label="s"]

        2->4[label="1", style=solid]
        2->0[label="0", style=dotted]
        4->14[label="1", style=solid]
        4->7[label="0", style=dotted]
        7->14[label="1", style=solid]
        7->0[label="0", style=dotted]
        14->1[label="1", style=solid]
        14->0[label="0", style=dotted]
}
```

#### Generated PNG

![case7](./assets/case7.png)



### Case 2 (5 variables)

$$
f(w, x, y, z, u) = \neg w \land x \land y \land z \land u + x \land y \land \neg z \land u + \neg w \land x \land \neg y \land z \land u + w \land x \land y \land \neg z \land \neg u
$$

#### Input PLA

[examples/case8/input.pla](../../examples/case8/input.pla)

```pla
.i 5
.o 1
.ilb w x y z u
.ob f
.p 4
01111 1
-1101 1
01011 1
11100 1
.e
```

#### Output DOT

```dot
digraph ROBDD{
        {rank=same 2}
        {rank=same 3 4}
        {rank=same 6 8}
        {rank=same 11 16}
        {rank=same 22}

        0[label=0, shape=box]
        1[label=1, shape=box]
        2[label="w"]
        3[label="x"]
        4[label="x"]
        6[label="y"]
        8[label="y"]
        11[label="z"]
        16[label="z"]
        22[label="u"]

        2->4[label="1", style=solid]
        2->3[label="0", style=dotted]
        3->6[label="1", style=solid]
        3->0[label="0", style=dotted]
        4->8[label="1", style=solid]
        4->0[label="0", style=dotted]
        6->22[label="1", style=solid]
        6->11[label="0", style=dotted]
        8->16[label="1", style=solid]
        8->0[label="0", style=dotted]
        11->22[label="1", style=solid]
        11->0[label="0", style=dotted]
        16->0[label="1", style=solid]
        16->1[label="0", style=dotted]
        22->1[label="1", style=solid]
        22->0[label="0", style=dotted]
}
```

#### Generated PNG

![case8](./assets/case8.png)