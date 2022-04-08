local M = {}

M.debug = true

local function print_text(message)
    if M.debug then
        print(message)
    end
end

---Save log to file. Return path string. For html return empty string.
---@param name string *Optional* Name for file. Default `sharelog`
---@param path string *Optional* Path to folder. Default `sys.get_save_file("sharelog", name)`
---@return string
function M.save_to_file(name, path)
    name = name or "sharelog"
    path = path or ""
    if html5 then
        html5.run("ShareLog.saveDebugInfo(\"" .. name .. "\")")
    else
        if path == "" then
            path = sys.get_save_file("sharelog", name) .. ".txt"
        else
            local last = string.sub(path, #path)
            if last ~= "/" and last ~= "\\" then
                path = path .. "/"
            end
            path = path .. name .. ".txt"
        end
        local log = sharelog_private.get_log_string()
        local file = io.open(path, "w+")
        io.output(file)
        io.write(log)
        io.close(file)
        print_text("File successfully saved to " .. path)
    end
    return path
end

---Return all log
---@return string
function M.get_log()
    if html5 then
        return html5.run("ShareLog.getDebugInfo()")
    else
        return sharelog_private.get_log_string()
    end
end

---Share text using share extention https://github.com/britzl/defold-sharing
function M.share_text()
    if share then
        local log = M.get_log()
        share.text(log)
        print_text("Text successfully send")
    else
        print_text("Share extention not active")
    end
end

---Share log as text to email
---@param email string
function M.share_to_email(email)
    assert(type(email) == "string", "Email must be string")
    local log = M.get_log()
    local link = "mailto:" .. email .. "?subject=Sharelog&body=" .. log
    local success = sys.open_url(link)
    if success then
        print_text("Email was created")
    else
        print_text("Email not created")
    end
end

---Share log as file using share extention https://github.com/britzl/defold-sharing
function M.share_file()
    if html5 and share then
        share.file(M.get_log(), "text/plain", "sharelog.txt")
    elseif share then
        local path = M.save_to_file()
        share.file(path)
        local success, err = os.remove(path)
        if success then
            print_text("File successfully removed from " .. path)
        else
            print_text("File not removed. " .. err)
        end
    else
        print_text("Share extention not active")
    end
end

---Check if share extention is available https://github.com/britzl/defold-sharing
---@return boolean
function M.is_share_work()
    if html5 then
        return share and html5.run("ShareLog.isNavigatorSupport()") == "true"
    else
        return share ~= nil
    end
end

return M
