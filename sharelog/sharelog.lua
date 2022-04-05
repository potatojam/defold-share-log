local M = {}

M.debug = true

local function print_text(message)
    if M.debug then
        print(message)
    end
end

function M.save_to_file(name, path)
    name = name or "sharelog"
    path = path or ""
    if html5 then
        html5.run("window.saveDebugInfo(\"" .. name .. "\")")
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
        local logs = sharelog_private.get_log_string()
        local file = io.open(path, "w+")
        io.output(file)
        io.write(logs)
        io.close(file)
        print_text("File successfully saved to " .. path)
    end
    return path
end

function M.get_info()
    if html5 then
        return html5.run("window.getDebugInfo()")
    else
        return sharelog_private.get_log_string()
    end
end

function M.share_text()
    if share then
        local log = M.get_info()
        share.text(log)
        print_text("Text successfully saved")
    else
        print_text("Share extention not active")
    end
end

function M.share_to_email(email)
    assert(type(email) == "string", "Email must be string")
    local log = M.get_info()
    local link = "mailto:" .. email .. "?subject=ShareLogs&body=" .. log
    local success = sys.open_url(link)
    if success then
        print_text("Email was created")
    else
        print_text("Email not created")
    end
end

function M.share_file()
    if share then
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

function M.is_share_work()
    return share ~= nil
end

return M
