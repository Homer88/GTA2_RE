import idaapi
import shutil
import idc
import os
import ida_idaapi



class BackupIDBPlugin(idaapi.plugin_t):
    # Удалите или закомментируйте эту строку, если атрибут не существует
	
    flags = idaapi.PLUGIN_PROC
	
    comment = "Авто-бэкап файла IDB"
    help = "Создает резервную копию текущего файла IDA"
    wanted_name = "i64 Backup"
    wanted_hotkey = "Ctrl-Shift-B"

    def init(self):
        print("Инициализация плагина BackupIDB")
        self.backup_idb()
        return idaapi.PLUGIN_OK

    def run(self, args):
        print("Запущен плагин BackupIDB")
        self.backup_idb()
        return 1

    def term(self):
        print("Выгрузка плагина BackupIDB")
    
    def backup_idb(self):
        backup_directory = r"F:\Github\GTA2_RE\re_file\IDA\ida_backups"
        path = idc.get_idb_path()
        print(path)
        idb_path = idc.get_idb_path()
        if idb_path and os.path.exists(idb_path):
            filename = os.path.basename(idb_path)
            backup_path = os.path.join(backup_directory, f"{filename}_{idaapi.IDA_SDK_VERSION}.IDB")
            try:
                shutil.copy2(idb_path, backup_path)
                print(f"Резервная копия создана: {backup_path}")
            except Exception as e:
                print(f"Ошибка при копировании файла: {e}")
        else:
            print("Файл IDB не найден или путь недоступен.")

def PLUGIN_ENTRY():
    return BackupIDBPlugin()