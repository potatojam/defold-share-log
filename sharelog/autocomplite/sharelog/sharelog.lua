---@class sharelog
local sharelog = {}

---Save log to file. Return path string. For html return empty string.
---@param name string *Optional* Name for file. Default `sharelog`
---@param path string *Optional* Path to folder. Default `sys.get_save_file("sharelog", name)`
---@return string
function sharelog.save_to_file(name, path)
end

---Return all log
---@return string
function sharelog.get_log()
end

---Share text using share extention https://github.com/britzl/defold-sharing
function sharelog.share_text()
end

---Share log to email
---@param email string
function sharelog.share_to_email(email)
end

---Share file using share extention https://github.com/britzl/defold-sharing
function sharelog.share_file()
end

---Check if share extention is available https://github.com/britzl/defold-sharing
function sharelog.is_share_work()
end

return sharelog
