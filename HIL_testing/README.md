# How to generate python metaclasses from Protocol buffers files:

    protoc -I="..\proto" --python_out="." ..\proto\MRAS.proto

Make sure `protoc` compiler is installed