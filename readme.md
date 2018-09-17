## 江淮青州项目第三方控制程序说明文档

1. 本程序用于江淮青州项目第三方控制FORI下线检测设备（不包含ABS）。

2. 本程序支持的操作系统，最低为：XP Pro SP3。

3. EOL_third_controller.exe为主程序，是命令行程序，没有GUI。启动后处于循环工作状态：
	- 获取VIN码 -> 从数据库中读取车型配置信息 -> 生成FORI检测设备的INI文件 -> 接受FORI发来的检测结果 -> 将结果写入数据库 -> 进入下一循环。

4. 运行时在控制台中直接执行主程序即可，无需其他参数。控制台中会输出相应软件运行信息，若出错的话会输出错误信息，并以黄底红字高亮显示。同时相应的运行信息会输出至log文件内，以备后续跟踪查找软件bug。

5. log目录为主程序log日志文件目录，存放主程序运行时生成的log文件，每个log文件以当天日期作为文件名。目录内的log文件数量最多为100个，多于100的话，会将修改时间较早的文件删除。

6. CaliProc目录内是EPS/EPB标定程序。如果本程序是用于定位仪工作站的话，在整个处理过程结束前会调用该目录内的标定程序，对车辆进行ECU标定。程序返回后整个处理过程才正式结束。

7. config目录为主程序配置文件目录，内有两个配置文件：
	- config.ini：主程序配置文件
	- INI_config.ini：生成发送给FORI检测设备的INI文件的配置文件

8. config.ini配置项说明：
	- Work_Station：四个工作站使用同一个程序，该配置用于区分用于哪一个工作站。用 `1`, `2`, `3`, `4` 整数来表示。
	- Send_File_Path：该节下的6个选项用来设置发送给FORI检测设备的INI文件的路径及文件名。
		- 除 `Dir`、`MaxFileNum` 外其余4个选项表示发送给FORI检测设备的INI文件名。文件名可以包含%VIN%这一个通配符，用来表示VIN码。例如：
			- 设传入的VIN码为 `testvincode012345` ，则 `Send_NCA_%VIN%.ini` 实际表示 `Send_NCA_testvincode012345.ini` 。
		- Dir：表示发送给FORI检测设备的INI文件所在的目录地址，可以是绝对路径也可以是相对路径。
		- MaxFileNum：表示在 `Dir` 目录下的可以存在的最多文件数量，若文件数量多于该选项的话，将会把修改时间最早的文件删除。若设为小于等于0的数值的话则不限制 `Dir` 目录下的文件数量。
	- Rece_File_Path：该节下的8个选项用来设置FORI发送过来的检测结果INI文件的路径和文件名，同样可以用%VIN%指代VIN码。各个选项意义同上一条。
	- DataBase：该节下的配置项用于配置SQL Server数据库参数。
		- IP：SQL Server数据库IP地址
		- Port：SQL Server数据库端口号
		- User：SQL Server登录账号的用户名，生产环境下建议不要使用默认管理员账号 `sa`
		- Pwd：SQL Server登录账号的密码
		- DBName：SQL Server使用的数据库名
	- Communication：该节用于配置主程序交换数据的接口参数。
		- INI_Config: `INI_config.ini` 配置文件的目录和文件名
		- Type: 主程序接受VIN码的方式，以 `1`, `2`, `3` 整数来表示
			- `1` : 串口
			- `2` : TCP/UDP
			- `3` : INI文件
		- Sleep_Time: 扫描VIN码的轮询时间，单位毫秒。指间隔 `Sleep_Time` 毫秒时间后尝试获取一次VIN码
		- Timeout: 工作站处理超时时间，单位秒。指工作站处理一辆车的超时时间，超过这个时间后程序强制进入下一个循环。
	- Serial_Port: 该节用于设置串口通讯参数
		- Port: 串口号
		- Baud_Rate: 波特率
		- Parity: 奇偶校验
		- Byte_Size: 数据位
		- Stop_Bits: 停止位
	- Socket: 该节用于设置TCP/UDP连接参数
		- Port: TCP/UDP连接端口号
		- Protocol: socket协议，用 `1`, `2` 整数来表示
			- `1` : TCP
			- `2` : UDP
	- INIVIN: 该节用于设置，通过INI文件方式读取VIN码的参数。主程序读取VIN码成功后，会将VIN码value值置空，进入下一循环后，其他程序将该value设为新的VIN码后，主程序再读取其值。
		- FullName: 含有VIN码的INI文件路径及文件名
		- Section: 含有VIN码的INI节名
		- Key: 含有VIN码的INI key名
9. INI_config.ini 配置项说明：
	- 该文件中每一节即为需要发给FORI检测设备的每个工作站INI文件
	- 每一节内key，value说明：
		- section_num: 表示该INI文件内一共有几个section
		- section{n}_name: {n}表示第几个section，该项表示该section的名字。
		- section{n}_start, section{m}_end: {n}表示第几个section，该两项表示从数据库内第n个字段开始到第m个字段为止生成INI，以0为起始值(不包括id字段)，若该字段为最后一个字段的话可以用-1表示。

10. 主程序接收VIN码的方式分为四种，分别是：串口、TCP、UDP、INI文件。
	- 串口：每一个数据包以 `0x02` 开头 `0x03` 结尾，其余数据均会被忽略。VIN码可以分成若干个包通过串口发送给主程序，以 `0x0D` , `0x0A` 结尾（即Windows系统的换行符）代表VIN码发送完毕。
	- TCP：由于TCP是面向连接的带有明确端口号的可靠传输方式，故无需数据封包的开头结尾标志，直接将VIN码发送给主程序即可，同样以换行符表示VIN码发送结束。
	- UDP：与TCP类似，但无需进行握手连接，同样无需数据封包的开头结尾标志，直接将VIN码发送给主程序即可，同样以换行符表示VIN码发送结束。
	- INI文件：节名为 `VIN` ，key名也为 `VIN` ，主程序成功读取VIN码后会置 `VIN` 的value值为空字符串。一辆车处理完毕后，其他程序再写 `VIN` 的value值为新的VIN码，主程序再次读取VIN码开始下一轮循环处理。
