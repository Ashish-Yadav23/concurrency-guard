import subprocess
import re

def run_binary(binary_path, iterations=20):
    print(f"\n>>> Testing: {binary_path}")
    print(f"{'Run #':<10} | {'Status':<10} | {'Balance':<15}")
    print("-" * 45)
    
    failures = 0
    passes = 0

    for i in range(1, iterations + 1):
        process = subprocess.run([binary_path], capture_output=True, text=True)
        output = process.stdout
        
        # Use Regular Expressions (Regex) to find the number after 'Actual Final Balance:'
        # This is how real SDET frameworks parse logs!
        match = re.search(r"Actual Final Balance:\s+(-?\d+)", output)
        
        if match:
            balance = int(match.group(1))
            if balance != 0:
                status = "FAIL ❌"
                failures += 1
            else:
                status = "PASS ✅"
                passes += 1
            print(f"Run {i:<8} | {status:<10} | {balance:<15}")
        else:
            # This happens if the C++ code crashes or output format changes
            print(f"Run {i:<8} | ERROR ⚠️    | Could not parse output")

    print("-" * 45)
    print(f"SUMMARY: {passes} Passed, {failures} Failed.")
    return failures

if __name__ == "__main__":
    v_fails = run_binary(".\\bank_vulnerable.exe")
    s_fails = run_binary(".\\bank_secure.exe")
    
    print("\n" + "="*45)
    if v_fails > 0 and s_fails == 0:
        print("FINAL VERDICT: SYSTEM VALIDATED ✅")
        print("Race condition detected in vulnerable build.")
        print("Mutex fix confirmed stable in secure build.")
    else:
        print("FINAL VERDICT: TEST INCONCLUSIVE ⚠️")
    print("="*45)