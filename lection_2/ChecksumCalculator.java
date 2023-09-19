import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class ChecksumCalculator {
    public static String calculateChecksum(String receivedString) {
        try {
            MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");

            byte[] bytes = receivedString.getBytes();
            byte[] checksumBytes = messageDigest.digest(bytes);

            StringBuilder checksum = new StringBuilder();
            for (byte b : checksumBytes) {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1) {
                    checksum.append('0');
                }
                checksum.append(hex);
            }
            return checksum.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void main(String[] args) {
        if (args.length == 1) {
            String receivedString = args[0];
            String checksum = calculateChecksum(receivedString);
            System.out.println("Checksum: " + checksum);
        } else {
            System.out.println("Please provide a single command line argument.");
        }
    }
}
