**预处理 `N` 和 `P` (模数)：** 

a.  **处理 `N=0`：** 如果输入的 `N` 是 0，直接输出 0。 

b.  **提取末尾的0：** 设输入为 $N_{original}$。计算 $N_{original}$ 末尾有多少个0，记为 `trailing_zeros`。 得到 $N_{effective} = N_{original} / (10^{trailing\_zeros})$。 如果 `trailing_zeros`是奇数，那么 $M^2$ 要得到奇数个末尾0是不可能的 (除非 $N_{original}=0$)。因此，如果 `trailing_zeros`是奇数且 $N_{original} \ne 0$，则无解，输出 "None"。

 c.  **确定有效模数 $P_{effective}$：** $P_{effective}$ 是 $10^k$，其中 $k$ 是 $N_{effective}$ 的位数。例如，如果 $N_{original} = 12300$，则 $trailing_{zeros} = 2$，$N_{effective} = 123$。`N_effective` 是3位数，所以 $P_{effective} = 10^3 = 1000$。 我们要解的是 $X^2 \equiv N_{effective} \pmod{P_{effective}}$。



**迭代构造解 $X$：**

a.  初始化当前处理的模数 `current_mod = 1`。 

b.  初始化候选解集合 `solutions = {0}`。因为任何数的平方模1都是0，而 $N_{effective} \pmod 1$ 也是0。所以0是模1下的一个平凡解。使用 `std::set<ll>` 来存储解，可以自动去重并保持有序。 

c.  **循环提升模数：** 当 $current\_mod < P_{effective}$ 时：

 i.  将下一个模数设为 $next\_mod = current\_mod * 10$。

 ii. 计算在下一个模数下的目标值 $target\_N\_mod\_next = N\_effective % next\_mod$。

 iii.创建一个空的 `next_solutions` 集合。 

iv. 对于 `solutions` 中的每一个旧解 `m_old` (它满足 $m_{old}^2 \equiv N_{effective} \pmod{current\_mod}$): 对于 `digit` 从 0 到 9: 构造新的候选解 $m\_candidate = m\_old + digit * current\_mod$。 检查是否 $(m_{candidate})^2 \equiv target\_N\_mod\_next \pmod{next\_mod}$。 

**注意：** $(m_{candidate})^2$ 可能会超过 `long long` 的范围，需要使用 `static_cast<__int128>` (GCC/Clang扩展) 或手动实现大数乘法取模。 如果满足条件，将 `m_candidate` 加入 `next_solutions`。 

v.  如果 `next_solutions` 为空，说明在当前步骤无法找到解，那么对于 $N_{effective}$ 就无解。可以提前终止。 

vi. 更新 `solutions = next_solutions`。

 vii.更新 `current_mod = next_mod`。



**获取最终解 $M$：** 

a.  如果迭代完成后 `solutions` 为空，或者中途确定无解，则原始的 `N_original` 无解，输出 "None"。 

b.  否则，从 `solutions` 中取出最小的元素，记为 $X_{min}$ (因为 `std::set` 是有序的，第一个元素就是最小的)。 

c.  最终的 $M = X_{min} \cdot 10^{\text{trailing\_zeros}/2}$。输出 `M`。



**缓存：** 

为了处理多个测试用例，可以将 `N_original` 和其对应的解 `M` (或-1代表无解) 存入 `std::map`。