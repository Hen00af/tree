# usage
```sh
cc tree.c -o tree

mkdir -p ~/.local/bin
cp ./tree ~/.local/bin
chmod +x ~/.local/bin/tree
```
and export it to PATH

```
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

then, you can use tree command.
