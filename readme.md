# subst

with -d you supply a variable and the contents directly and with -f you instruct subst to use the contents of the designated file.
-s swallows trailing newlines in files
```subst infile [-d VARNAME VARCONTENT] [-f VARNAME VARFILE]```

# building
just run ```cc subst.c -o subst```
