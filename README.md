# Share Log for Defold

The extension writes all output data to the console and makes it possible to receive them as a string, or send them.

## Installation

You can use it in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/). Open your `game.project` file and in the dependencies field add **a link to the ZIP file of a [specific release](https://github.com/potatojam/defold-share-log/tags).**

> &#x26a0;&#xfe0f; For some functions, you need to use the [share](https://github.com/britzl/defold-sharing) extension. https://github.com/britzl/defold-sharing

## The `game.project` Settings

```ini
[share_log]
block_release_version = true
catch_promise_errors = true
force_html5_init = false
```

* `block_release_version` - Disable record for release version.
* `catch_promise_errors` - For `html5` version. Records unhandled promise errors.
* `force_html5_init` - For `html5` version. Starts recording on page load, not extension. The extension is initialized a bit later. Ignored `block_release_version` parameter.

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

