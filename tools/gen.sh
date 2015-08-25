mkdir -p output
GEN=/home/lixianjing/work/lab/cantk/v8-native-binding-generator/gen-v8-binding.js

node $GEN idl/location.json
node $GEN idl/screen.json
node $GEN idl/fs.json
node $GEN idl/image.json
node $GEN idl/canvas.json
node $GEN idl/context_render_2d.json
node $GEN idl/http_client.json
