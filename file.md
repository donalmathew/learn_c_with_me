### 1. Opening a file:
```c
FILE *fp;
fp=fopen("input.txt","r");
```

### 2. Reading:
#### 2.1 By Character:
- Get one Character:
    ```c
    char c;

    c = fgetc(fp);
    printf("%c", c);
    ```
- looping the character:
    ```c
    int c;

    while ((c = fgetc(fp)) != EOF)
        printf("%c", c);
    ```
    >The variable c is declared as an int to handle both character values and the EOF condition effectively. The EOF itself is defined as -1, which cannot be represented by a regular character type without losing its significance. Thus, this design choice ensures robust file reading operations in C programming.

#### 2.2 Reading a Line at a Time
- using fgets:
    ```c
    char s[1024];

    while (fgets(s, sizeof s, fp) != NULL) 
        printf("%s",s);
    ```

#### 2.3 Formatted input:
- from textbook:
    ```txt
    input.txt:

        blue 29.9 173
        right 20.7 135
        gray 14.9 41
        humpback 16.0 30
    ```
    ```c
    char name[1024];
    float length;
    int mass;

    while (fscanf(fp, "%s %f %d", name, &length, &mass) != EOF)
        printf("%s whale, %d tonnes, %.1f meters\n", name, mass, length);
    ```
    ```txt
    output.txt:
        
        blue whale, 173 tonnes, 29.9 meters

        right whale, 135 tonnes, 20.7 meters

        gray whale, 41 tonnes, 14.9 meters
        
        humpback whale, 30 tonnes, 16.0 meters
    ```

- how i usually do:
    ```c
    char buffer[1024];

    while(!feof(fp))
    {
        fscanf(fp,"%s",buffer);

        fprintf(fp1," %c ",buffer[i]);
    }

### 3. Writing:

 ```c
 int x = 32;


 fputc('B', fp); //method 1

 fprintf(fp, "x = %d\n", x); //method 2

 fputs("Hello, world!\n", fp); //method 3
 ```
 ```txt
 output.txt:

 B
x = 32
Hello, world!
```