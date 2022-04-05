local M = {}

function M.save_to_file()
    if html5 then
        html5.run("window.saveDebugInfo()")
    else
        pprint("HTML Log only works in html")
    end
end

function M.get_info()
    if html5 then
        return html5.run("window.getDebugInfo()")
    else
        pprint("HTML Log only works in html")
        return ""
    end
end

return M
