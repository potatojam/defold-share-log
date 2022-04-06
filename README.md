# Share Log for Defold

## Installation

You can use it in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/). Open your `game.project` file and in the dependencies field add **a link to the ZIP file of a [specific release](https://github.com/potatojam/defold-share-log/tags).**

> &#x26a0;&#xfe0f; For some functions, you need to use the [share](https://github.com/britzl/defold-sharing) extension. https://github.com/britzl/defold-sharing

## Lua API

For use the functions you need to require module:

```lua
local sharelog = require("sharelog.sharelog")
```

### `sharelog.get_log()`

**Return** all log as `string`

### `sharelog.save_to_file([, name[, path]])`

Save log to file. **Return** path as `string`. For **html** return empty `string`.

**Parameters**

- `name` <kbd>string|nil</kbd> _optional_ Name for file. Default `sharelog`
- `path` <kbd>string|nil</kbd> _optional_  Path to folder. Default `sys.get_save_file("sharelog", name)`

### `sharelog.share_to_email(email)`

Share log to email where possible.

**Parameters**

- `email` <kbd>string</kbd> _required_ Email to send
  
### `sharelog.share_text()`

Share log as text using [share](https://github.com/britzl/defold-sharing) extension

### `sharelog.share_file()`

Share file as text using [share](https://github.com/britzl/defold-sharing) extension

### `sharelog.is_share_work()`

Check if [share](https://github.com/britzl/defold-sharing) extention is available **Return** `boolean`

## Credits

Made by [PotatoJam](https://github.com/potatojam).

For example used:

[Dirty Larry](https://github.com/andsve/dirtylarry)

### License

MIT license.

