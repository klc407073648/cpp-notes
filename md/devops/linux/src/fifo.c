    fd = open(argv[1], O_WRONLY);
    if (fd < 0) 
        sys_err("open");

    i = 0;
    while (1) {
        sprintf(buf, "hello itcast %d\n", i++);

        write(fd, buf, strlen(buf));
        sleep(1);
    }

[root@192 fifo]# ./fifo_w klc.txt


    fd = open(argv[1], O_RDONLY);
    if (fd < 0) 
        sys_err("open");
    while (1) {
        len = read(fd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        sleep(3);           
    }

[root@192 fifo]# ./fifo_r klc.txt
hello itcast 0
hello itcast 1
