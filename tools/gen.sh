mkdir -p output
node /work/lab/cantk/v8-native-binding-generator/gen-v8-binding.js idl/location.json
node /work/lab/cantk/v8-native-binding-generator/gen-v8-binding.js idl/screen.json
node /work/lab/cantk/v8-native-binding-generator/gen-v8-binding.js idl/fs.json
node /work/lab/cantk/v8-native-binding-generator/gen-v8-binding.js idl/image.json
node /work/lab/cantk/v8-native-binding-generator/gen-v8-binding.js idl/canvas.json
node /work/lab/cantk/v8-native-binding-generator/gen-v8-binding.js idl/context_render_2d.json
node /work/lab/cantk/v8-native-binding-generator/gen-v8-binding.js idl/http_client.json
