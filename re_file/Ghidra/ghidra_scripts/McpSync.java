// @category MCP
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Namespace;
import ghidra.program.model.symbol.SourceType;
import java.io.BufferedReader;
import java.io.FileReader;

public class GhidraSync extends GhidraScript {
    @Override
    public void run() throws Exception {
        String list = "C:\\Users\\Home\\AppData\\Local\\Temp\\opencode\\ghidra_rename_list.txt";
        int ok = 0, skip = 0, fail = 0;
        try (BufferedReader br = new BufferedReader(new FileReader(list))) {
            String line;
            while ((line = br.readLine()) != null) {
                if (line.trim().isEmpty()) continue;
                String[] p = line.split(";", 2);
                if (p.length != 2) continue;
                String addrStr = p[0].trim();
                String newName = p[1].trim();
                if (!newName.contains("::")) { skip++; continue; }
                Address addr = toAddr(addrStr);
                if (addr == null) { fail++; println("bad addr " + addrStr); continue; }
                Function f = getFunctionAt(addr);
                if (f == null) { fail++; println("no func " + addrStr); continue; }
                String[] clsFn = newName.split("::", 2);
                String cls = clsFn[0];
                String fnn = clsFn[1];
                try {
                    Namespace ns = getOrCreateNamespace(cls);
                    f.setParentNamespace(ns);
                    f.setName(fnn, SourceType.USER_DEFINED);
                    ok++;
                } catch (Exception e) {
                    fail++; println("fail " + addrStr + " " + e);
                }
            }
        }
        println("DONE ok=" + ok + " skip=" + skip + " fail=" + fail);
    }
}
